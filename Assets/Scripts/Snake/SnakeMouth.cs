using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[DisallowMultipleComponent]
[RequireComponent(typeof(MeshCollider))]
public class SnakeMouth : MonoBehaviour
{
    #region Parameters
    [SerializeField, Min(0.0f)] private float coneWidth = 0.5f;
    [SerializeField, Min(0.0f)] private float eatDistance = 2.0f;
    [SerializeField, Min(0.0f)] private float absorptionRate = 0.5f;
    [SerializeField] private TagProvider tagProvider = null;

    private const int one = 1, two = 2, zero = 0;

    private MeshCollider mouthCollider = null;
    #endregion

    #region MonoBehaviour API
    private void Awake()
    {
        mouthCollider = GetComponent<MeshCollider>();
    }

    private void Start()
    {
        CreateMeshCone();
    }

    private void OnTriggerStay(Collider collider)
    {
        if (collider.CompareTag(tagProvider.FoodTag))
        {
            collider.transform.LookAt(transform.parent);
            collider.transform.Translate(collider.transform.forward * absorptionRate * Time.deltaTime);
        }
    }
    #endregion

    #region Custom methods
    private void CreateMeshCone()
    {
        Mesh coneMesh = new Mesh()
        {
            name = "Mouth cone",
            vertices = new Vector3[] { new Vector3(coneWidth, zero, eatDistance), new Vector3(-coneWidth, zero, eatDistance), new Vector3(zero, zero, zero) },
            uv = new Vector2[] { new Vector2(zero, one), new Vector2(one, one), new Vector2(zero, zero) },
            triangles = new int[] { zero, one, two }
        };

        mouthCollider.sharedMesh = coneMesh;
    }
    #endregion
}
